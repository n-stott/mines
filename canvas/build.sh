SRC_DIR="../src"
THIRDPARTY_DIR="../third-party"

rm -r _build
mkdir _build
cd _build

reset

g++ -std=c++11 -Ofast -w \
 -I$THIRDPARTY_DIR/eigen \
-o canvas \
$SRC_DIR/*.cpp \
-lGL -lGLU -lglut

./canvas