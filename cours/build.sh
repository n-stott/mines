SRC_DIR="../src"
THIRDPARTY_DIR="../third-party"

reset

rm -r _build
mkdir _build
cd _build

g++ -std=c++11 -g -Ofast -I$THIRDPARTY_DIR/eigen -o demo -w $SRC_DIR/*.cpp -lGL -lGLU -lglut
