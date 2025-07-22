


run:
	cmake -S . -B ./bin/
	make -C ./bin
	mkdir -p ~/.local/bin/
	cp ./bin/src/auto-click ~/.local/bin/

	auto-click -S .1 \
		-p \
		-d 1.0 \
		-i 2 \
		-D 1.5