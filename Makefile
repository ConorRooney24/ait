src := src/main.c src/ait_file_io_helpers.c src/ait_splash_screen.c src/invocation_config/ait_invocation_config.c

build: $(src)
	mkdir -p build
	gcc $(src) -o build/ait

run: build
	build/ait

clean:
	rm -rf build
