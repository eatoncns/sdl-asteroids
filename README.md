# sdl-asteroids
Repo for SDL asteroids game

Build requirements (linux/macosx):

- SDL2
- $BOOST_INCLUDE environment variable set to directory containing boost headers
- $GMOCK_INCLUDE environment variable set to directory containing gmock headers
- $GMOCK_LIB environment variable set to directory containing libgmock.a

Build and run unit tests with

./gradlew build


Run the game with

./gradlew run
