use std::io::Write;
use std::process::{Command, Stdio};

fn main() {
    // Call to 'blocking' output()
    let mut date_cmd = Command::new("date");

    let out_str = String::from_utf8(date_cmd.output().unwrap().stdout.to_vec()).expect("Cannot convert Vec<u8> into String");
    println!("out: {}", out_str);
    let out_str = String::from_utf8(date_cmd.arg("--utc").output().unwrap().stdout.to_vec()).expect("Cannot convert Vec<u8> into String");
    println!("out: {}", out_str);

    // Spawning int separate thread ('non-blocking' spawn)
    let mut rev_cmd = Command::new("rev")
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .spawn()
        .unwrap();

    let mut std_in = rev_cmd.stdin.take().unwrap();
    //let mut std_out = rev_cmd.stdout.take().unwrap();

    std::thread::spawn(move || {
        std_in.write_all("Hello World".as_bytes()).unwrap();
    });

    let output = rev_cmd.wait_with_output().unwrap();
    println!("out from rev: {}", String::from_utf8_lossy(&output.stdout));
}
