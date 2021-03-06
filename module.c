#include <linux/module.h>
#include "funchook.h"

/* heades needed by patched function */
#include <net/sock.h>

/* module param defines */


/*
 * 1.use HOOK_DEFINE macro to define the hook function.
 *  1.1 if you need to call the original function in the hook function,
 *      you need to use CALL_ORIG_FUNCION macro.
 *  1.2 if you need to call other kernel exported function, just include the
 *      related header(s).
 *  1.3 if you need to call other kernel static function, you need to make a
 *      duplicate copy here.
 */
HOOK_DEFINE(fput, void, struct file *file)
{
	pr_info("before fput: file=%p\n", file);

	CALL_ORIG_FUNCION(fput, file);

	pr_info("after fput: file=%p\n", file);
}

static __init int funchook_init(void)
{
	int ret = 0;

	/*
	 * 2. use HOOK_REGISTER macro to replace original function with hook function
	 */
	ret = HOOK_REGISTER(fput);
	if (ret != 0)
	{
		pr_info("fput failed ret=%d\n", ret);
		return ret;
	}


	return ret;
}
module_init(funchook_init);

static __exit void funchook_exit(void)
{
	/*
	 * 3. use HOOK_UNREGISTER macro to restore original function.
	 */
	HOOK_UNREGISTER(fput);
}
module_exit(funchook_exit);

MODULE_DESCRIPTION("hook sample");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");
