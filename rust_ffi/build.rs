fn main() {
    cc::Build::new().file("src/c_code.c").compile("c_code");
    println!("cargo:rerun-if-changed=c_code.c");

    println!("cargo:rustc-link-lib=dylib=ncurses");
}
