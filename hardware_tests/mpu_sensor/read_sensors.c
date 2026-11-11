#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>

void read_sensor(const char* bus_name, int address) {
    int fd = open(bus_name, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return;
    }

    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        perror("Failed to connect to sensor address");
        close(fd);
        return;
    }

    // 1. Wake up the MPU-6050 
    char config[2] = {0x6B, 0x00};
    if (write(fd, config, 2) != 2) {
        perror("Failed to wake up MPU-6050");
        close(fd);
        return;
    }

    // GIVE THE SENSOR 10ms TO STABILIZE AFTER WAKING UP
    usleep(10000); 

    // 2. Request data starting from register 0x3B
    char reg = 0x3B;
    if (write(fd, &reg, 1) != 1) {
        perror("Failed to set register pointer");
        close(fd);
        return;
    }

    // 3. Read 6 consecutive bytes
    char buf[6];
    if (read(fd, buf, 6) != 6) {
        perror("Failed to read sensor data");
    } else {
        int16_t ax = (buf[0] << 8) | buf[1];
        int16_t ay = (buf[2] << 8) | buf[3];
        int16_t az = (buf[4] << 8) | buf[5];

        printf("Bus: %-10s | Addr: 0x%02X -> Accel X: %5d | Y: %5d | Z: %5d\n", 
               bus_name, address, ax, ay, az);
    }

    close(fd);
}

int main() {
	printf("Starting live sensor stream. Press ctrl+c to stop.\n\n");

	while(1){
		// Read all three sensors sequentially
    		read_sensor("/dev/i2c-1", 0x68);
    		read_sensor("/dev/i2c-1", 0x69);
    		read_sensor("/dev/i2c-3", 0x68);

		printf("---\n");
		// wait 20 ms between refreshes
		usleep(200000);
	}
    	return 0;
}
