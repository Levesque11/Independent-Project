#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>      
#include <linux/device.h>  
#include <linux/uaccess.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Justin Levesque");
MODULE_DESCRIPTION("Multi-MPU-6050 I2C Ring 0 Driver");
MODULE_VERSION("1.0");

#define DEVICE_NAME "drone_sensor"
#define CLASS_NAME "drone_class"
#define MAX_SENSORS 3

static int major_number = 0;
static struct class *drone_class = NULL;
static int sensor_count = 0; 

// necessary kernel headers and cap the hardware limit at three sensors
// Set up a tracking variable for the count and an array to store each client connection
struct drone_sensor_data {
    struct i2c_client *client;
    int minor_number;
};
static struct drone_sensor_data sensors[MAX_SENSORS];

static int drone_open(struct inode *inodep, struct file *filep) {
    int minor = iminor(inodep);
    
    if (minor >= MAX_SENSORS || sensors[minor].client == NULL) {
        return -ENODEV; 
    }
    
    // getting the minor number so we know exactly which of the three device files the daemon is opening
    // keep track of the sensor into private_data so the read function knows which one to talk to
    filep->private_data = &sensors[minor];
    return 0;
}

static int drone_release(struct inode *inodep, struct file *filep) {
    return 0;
}

static ssize_t drone_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    char message[150]; // Increased buffer size for the larger JSON
    int message_len, uncopied_bytes;
    s16 accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z;
    
    struct drone_sensor_data *sensor = filep->private_data;

    if (*offset > 0) return 0; 
    if (sensor->client == NULL) return -EFAULT;

    // Read Accelerometer
    accel_x = i2c_smbus_read_word_swapped(sensor->client, 0x3B);
    accel_y = i2c_smbus_read_word_swapped(sensor->client, 0x3D);
    accel_z = i2c_smbus_read_word_swapped(sensor->client, 0x3F);

    // Read Gyroscope
    gyro_x = i2c_smbus_read_word_swapped(sensor->client, 0x43);
    gyro_y = i2c_smbus_read_word_swapped(sensor->client, 0x45);
    gyro_z = i2c_smbus_read_word_swapped(sensor->client, 0x47);

    // Pack it all into the Ring 3 bridge
    snprintf(message, sizeof(message), 
             "{\"sensor\": %d, \"accel_x\": %d, \"accel_y\": %d, \"accel_z\": %d, \"gyro_x\": %d, \"gyro_y\": %d, \"gyro_z\": %d}\n", 
             sensor->minor_number, accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
    
    message_len = strlen(message);
    uncopied_bytes = copy_to_user(buffer, message, message_len);

    if (uncopied_bytes == 0) {
        *offset += message_len;
        return message_len;
    } else {
        return -EFAULT;
    }
}

// send the standard Linux file operations over to our custom Ring 0 functions
// This is what the kernel uses when the daemon tries to interact with our device files
static struct file_operations drone_fops = {
    .owner = THIS_MODULE,
    .open = drone_open,
    .read = drone_read,
    .release = drone_release,
};

static int drone_sensor_probe(struct i2c_client *client, const struct i2c_device_id *id) {
    int minor = sensor_count;
    if (minor >= MAX_SENSORS) return -ENOMEM;

    // Turn off sleep mode by writing to the register and save this client to the array
    // Generate a dedicated device file for this specific sensor using its minor number
    i2c_smbus_write_byte_data(client, 0x6B, 0x00);
    
    sensors[minor].client = client;
    sensors[minor].minor_number = minor;

    i2c_set_clientdata(client, &sensors[minor]);

    device_create(drone_class, NULL, MKDEV(major_number, minor), NULL, "%s_%d", DEVICE_NAME, minor);
    
    printk(KERN_INFO "[DRONE] MPU-6050 probed at 0x%02x, created /dev/%s_%d\n", client->addr, DEVICE_NAME, minor);
    sensor_count++;
    return 0; 
}

static void drone_sensor_remove(struct i2c_client *client) {
    struct drone_sensor_data *sensor = i2c_get_clientdata(client);
    
    // Retrieve the specific sensor that is disconnecting and destroy its unique device file
    // Clear out the client pointer in the array so we do not cause a fatal kernel crash later
    if (sensor) {
        device_destroy(drone_class, MKDEV(major_number, sensor->minor_number));
        sensor->client = NULL;
        printk(KERN_INFO "[DRONE] /dev/%s_%d destroyed.\n", DEVICE_NAME, sensor->minor_number);
    }
}

// Link our custom probe and remove functions directly to the I2C driver structure
// This tells the operating system exactly what to run when an MPU-6050 is plugged in
static const struct i2c_device_id drone_sensor_id[] = {
    { "drone-mpu", 0 }, 
    { }               
};
MODULE_DEVICE_TABLE(i2c, drone_sensor_id);

static struct i2c_driver drone_sensor_driver = {
    .driver = {
        .name = "drone_sensor",
        .owner = THIS_MODULE,
    },
    .probe = drone_sensor_probe,
    .remove = drone_sensor_remove,
    .id_table = drone_sensor_id,
};

static int __init drone_init(void) {
    // Run this one time at load to secure the major number and build the base class directory
    // Register the I2C driver so the system actively starts looking for our hardware on the buses
    major_number = register_chrdev(0, DEVICE_NAME, &drone_fops);
    drone_class = class_create(THIS_MODULE, CLASS_NAME);
    
    printk(KERN_INFO "[DRONE] Base driver loaded. Waiting for sensors...\n");
    return i2c_add_driver(&drone_sensor_driver);
}

static void __exit drone_exit(void) {
    // Stop listening for I2C devices
    // Hand the major number back to the kernel 
    i2c_del_driver(&drone_sensor_driver);
    class_destroy(drone_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "[DRONE] Base driver unloaded.\n");
}

module_init(drone_init);
module_exit(drone_exit);
