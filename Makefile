src := src/main.c src/helpers/ait_file_io_helpers.c src/ait_splash_screen.c src/invocation_config/ait_invocation_config.c src/invocation_config/ait_arg_parse.c src/invocation_config/ait_cmd.c src/invocation_config/ait_cmd_opt.c src/invocation_config/ait_global_opt.c src/config/ait_config.c src/config/ait_config_parse.c src/helpers/ait_dynamic_array.c

build: $(src)
	mkdir -p build
	gcc $(src) -o build/ait

run: build
	build/ait

clean:
	rm -rf build
