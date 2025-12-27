


run:
	cmake -S . -B ./bin/
	make -C ./bin
	mkdir -p ~/.local/bin/
	cp ./bin/src/auto-click ~/.local/bin/

	auto-click -r