SRC_DIR="../src"
THIRDPARTY_DIR="../third-party"

mkdir _build
cd _build

g++ -std=c++11 -Ofast \
 -I$THIRDPARTY_DIR/eigen \
-o app_boids \
$SRC_DIR/*.cpp \
-lGL -lGLU -lglut
