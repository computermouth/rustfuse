extern crate cc;
extern crate pkg_config;

fn main() {
    cc::Build::new()
        .file("src/cfuncs.c")
        .compile("libcfuncs.a");

    pkg_config::Config::new().statik(true).probe("sdl2").unwrap();
    
}
