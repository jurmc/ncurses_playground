fn main() {
    cc::Build::new().file("src/drops.c").compile("drops");
    cc::Build::new().file("src/get_rand.c").compile("get_rand");

    println!("cargo:rustc-link-lib=dylib=ncurses");

    println!("cargo:rerun-if-changed=drops.c");
    println!("cargo:rerun-if-changed=drops.h");
}
