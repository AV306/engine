# engine

2D SFML game engine of sorts.

<br>

## stuff

- Tile-based maps
- update() method for entities like Unity
- It works :D

## limitations

- Map tilesets can only contain a maximum of 255 tiles (about 16x16), because the map format currently only allocates 1 byte for the tile index
- Engine will crash with a segfault if a non-existent texture is loaded
- Implementation-inheritance based "component" system instead of object-composition (SFML uses implementation inheritance for Drawable and Transform, so for parity I decided to follow it for Collider)

## building

### linux with apt

1. Clone the repo (I can't believe you have to explicitly tell GitHub Actions this. otherwise it just runs in an empty repo)
2. Install the dependencies through `./install_deps` (Installs Cate and SFML)
3. Run `cate` in the project root
4. Find the executable in `out/`

### windows with MSYS2

\* Note: I personally haven't gotten this to work

Same as linux, except you have to cross-compile cate from a linux machine

## running

```bash
./out/game --asset-dir="/path/to/asset/directory/"
```

## credits

- [TheMilkies/Cate](https://github.com/TheMilkies/Cate): The best C++ build system you'll ever have.
- [Darren Mulholland/Args++](http://www.dmulholl.com/docs/argspp/master/index.html): The simplest and easiest-to-use arg-parsing library out there by far.
