use core::ffi::c_int;
use core::ffi::c_char;
use core::ffi::c_uchar;
use core::ffi::c_short;
use std::ffi::CString;
use std::ffi::CStr;

#[repr(C)]
pub struct StructWithArray {
    fields: *mut c_int,
    size: usize,
}

extern "C" {
    fn dump_c_char(v: c_char);
    fn dump_c_unsigned_char(v: c_uchar);
    fn dump_c_short(v: c_short);
    fn dump_c_string(s: *const i8);
    fn dump_c_struct_containing_array(arr: *const StructWithArray);
    fn modify_c_struct_containing_array(arr: *mut StructWithArray);

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

fn dump_array(arr: &[c_int]) {
    for item in arr {
        println!("[R] array item: {}", item);
    }
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

        let mut arr: [c_int; 8] = [1, 2, 3, 4, 5, 6, 7, 8];
        dump_array(&arr);
        let mut struct_with_array = StructWithArray {
            fields: arr.as_mut_ptr(),
            size: 8,
        };
        dump_c_struct_containing_array(&struct_with_array);
        modify_c_struct_containing_array(&mut struct_with_array);
        println!("-------------------------");
        dump_c_struct_containing_array(&struct_with_array);

        let mut v = vec![1, 2, 3, 4, 5];
        let mut struct_with_array_from_vec = StructWithArray {
            fields: v.as_mut_ptr(),
            size: v.len(),
        };
        dump_c_struct_containing_array(&struct_with_array_from_vec);
        modify_c_struct_containing_array(&mut struct_with_array_from_vec);
        println!("-------------------------");
        dump_c_struct_containing_array(&struct_with_array_from_vec);
    }
}
