#include "lua_c.h"
#include <unistd.h>

int main()
{
	init_lua();
	regist_func_to_lua();
	load_lua_files();

	printf("== sum test ==\n");
	int sum = proc_add_operation(100, 200);
	printf("sum is %d\n\n", sum);

	printf("== check value test ==\n");
	bool right = proc_check_value(300);
	if (right) {
		printf("check right\n\n");
	}

	printf("== check runtime changes ==\n");
	while(1) {
		sleep(1);
		load_lua_files();
		int result = proc_runtime_changes(400);
		printf("runtime changes %d \n", result);
	}

	final_lua();
	return 0;
}
