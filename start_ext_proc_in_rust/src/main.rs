use std::process::Command;

fn main() {
    let output = Command::new("echo")
        .arg("Hello, my world!")
        .output()
        .expect("Failed to executed command");


    let out_str = String::from_utf8(output.stdout.to_vec()).expect("Cannot convert Vec<u8> into String");
    println!("out: {}", out_str);
}
