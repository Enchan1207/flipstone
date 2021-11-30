#
#
#

.PHONY: configure build

# cmakeを使用してプロジェクトをビルドする。ビルドディレクトリが存在しない場合は先に configure を実行する。
build:
	@if [ ! -d ./build ]; then $(MAKE) configure;fi
	cmake --build build --config Debug --target all

configure:
	cmake \
		--no-warn-unused-cli \
		-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
		-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
		-S. \
		-Bbuild \
		-GNinja
