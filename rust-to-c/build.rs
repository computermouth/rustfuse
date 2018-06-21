extern crate cc;
extern crate pkg_config;

fn main() {
    cc::Build::new()
        .file("src/double.c")
        .compile("libdouble.a");

    pkg_config::Config::new().statik(true).probe("libconfuse").unwrap();

//    println!("cargo:rustc-link-lib=static=confuse");
}
