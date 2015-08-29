# sdl-asteroids
Repo for SDL asteroids game

Build requirements (linux):

- Gradle (n.b. build.gradle written using features incubating in Gradle 2.5)
- $BOOST_INCLUDE environment variable set to directory containing boost headers
- $GMOCK_INCLUDE environment variable set to directory containing gmock headers
- $GMOCK_LIB environment variable set to directory containing libgmock.a

Build and run unit tests with

gradle build


Run the game with

gradle run
