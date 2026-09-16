#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0x53ef4b37, "__register_chrdev" },
	{ 0x1ab96da8, "__class_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x513f59f9, "device_create" },
	{ 0x5e1d2b89, "class_destroy" },
	{ 0x17b60882, "device_destroy" },
	{ 0xfd163b77, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "B2CA23713AB5528D1F73CC5");
