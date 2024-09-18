use core::ffi::c_char;
use core::ffi::c_uchar;
use core::ffi::c_short;
use std::ffi::CString;
use std::ffi::CStr;

extern "C" {
    fn dump_c_char(v: c_char);
    fn dump_c_unsigned_char(v: c_uchar);
    fn dump_c_short(v: c_short);
    fn dump_c_string(s: *const i8);

    fn dump_all();

    fn dump_p_c_char(v: *const c_char);
    fn dump_p_c_unsigned_char(v: *const c_uchar);
    fn dump_p_c_short(v: *const c_short);

}

fn dump_i8(v: i8) {
    println!("[R] i8 v: {}", v);
}

fn dump_u8(v: u8) {
    println!("[R] u8 v: {}", v);
}

fn dump_i16(v: i16) {
    println!("[R] i16 v: {}", v);
}

fn dump_string(s: &str) {
    println!("[R] String s: {:?}", s);
}

fn main() {

    unsafe {
        let c: i8 = 97;
        dump_c_char(c);
        dump_p_c_char(&c);
        dump_i8(c);

        let c: u8 = 200;
        dump_c_unsigned_char(c);
        dump_p_c_unsigned_char(&c);
        dump_u8(c);


        let s: i16 = 1024;
        dump_c_short(s);
        dump_p_c_short(&s);
        dump_i16(s);

        let rust_string = String::from("Litwo, Ojczyzno moja...");
        let c_string = CString::new(rust_string.clone()).unwrap();
        let c_str: &CStr = c_string.as_c_str();
        dump_c_string(c_str.as_ptr());
        dump_string(&rust_string);

//        println!("-------------------------");
//        dump_all();
    }
}
