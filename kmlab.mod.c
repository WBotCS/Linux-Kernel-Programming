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


static const char ____versions[]
__used __section("__versions") =
	"\x14\x00\x00\x00\x0f\xcd\xe2\x5b"
	"proc_mkdir\0\0"
	"\x14\x00\x00\x00\x5b\x84\x7a\x72"
	"proc_create\0"
	"\x1c\x00\x00\x00\x5d\xe6\x36\x03"
	"remove_proc_entry\0\0\0"
	"\x24\x00\x00\x00\x52\x3f\x0a\x4b"
	"gic_nonsecure_priorities\0\0\0\0"
	"\x10\x00\x00\x00\xd8\x7e\x99\x92"
	"_printk\0"
	"\x10\x00\x00\x00\xad\x64\xb7\xdc"
	"memset\0\0"
	"\x18\x00\x00\x00\x14\x27\x52\x8d"
	"__rcu_read_lock\0"
	"\x14\x00\x00\x00\x23\xa4\x27\x7b"
	"find_vpid\0\0\0"
	"\x14\x00\x00\x00\xd4\x72\x4c\x2f"
	"pid_task\0\0\0\0"
	"\x1c\x00\x00\x00\x0f\x81\x69\x24"
	"__rcu_read_unlock\0\0\0"
	"\x10\x00\x00\x00\xfd\xf9\x3f\x3c"
	"sprintf\0"
	"\x20\x00\x00\x00\xdd\xb7\x9c\x61"
	"simple_read_from_buffer\0"
	"\x1c\x00\x00\x00\x5b\x73\xba\x65"
	"__stack_chk_fail\0\0\0\0"
	"\x1c\x00\x00\x00\x48\x9f\xdb\x88"
	"__check_object_size\0"
	"\x14\x00\x00\x00\xcb\x69\x85\x8c"
	"kstrtoint\0\0\0"
	"\x18\x00\x00\x00\x64\xbd\x8f\xba"
	"_raw_spin_lock\0\0"
	"\x18\x00\x00\x00\xb6\x6f\xf1\x24"
	"kmalloc_caches\0\0"
	"\x18\x00\x00\x00\xa0\xfa\x90\x2b"
	"kmalloc_trace\0\0\0"
	"\x1c\x00\x00\x00\x34\x4b\xb5\xb5"
	"_raw_spin_unlock\0\0\0\0"
	"\x1c\x00\x00\x00\x31\x92\x07\x6b"
	"alt_cb_patch_nops\0\0\0"
	"\x18\x00\x00\x00\x30\xfb\x88\xb7"
	"gic_pmr_sync\0\0\0\0"
	"\x20\x00\x00\x00\x28\xe1\xa4\x12"
	"__arch_copy_from_user\0\0\0"
	"\x14\x00\x00\x00\x97\x2c\x07\x6e"
	"cpu_hwcaps\0\0"
	"\x18\x00\x00\x00\x4e\xba\x82\x76"
	"__copy_overflow\0"
	"\x18\x00\x00\x00\x1a\x56\x33\x13"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1F1DC7821171223EFDFD1D3");
