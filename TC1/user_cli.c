#include "main.h"

#ifdef USE_DEBUG_CLI

#include "mico_system.h"
#include "user_function.h"

static void user_echo (char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv) {
	cli_printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++) {
		cli_printf("%s, ", argv[i]);
	}
}

static void user_cli_cmd (char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv) {
	if (argc == 1) return;
	user_function_cmd_received(
			(argc >= 3) ? argv[2] : "",
			argv[1]);
}

static const struct cli_command user_cli_commands[] = {
	{"userecho", NULL, user_echo},
	{"usercmd", "usercmd cmd [topic]: feed command to user_function_cmd_received", user_cli_cmd}
};

int user_cli_init(void) {
	return cli_register_commands(user_cli_commands,
			sizeof(user_cli_commands) / sizeof(user_cli_commands[0]));
}
#else
int user_cli_init(void) {
	return 0;
}
#endif
