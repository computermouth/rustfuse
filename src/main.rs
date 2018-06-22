extern crate libc;

use std::ffi::CString;

extern {
    fn init(title: *const libc::c_char, width: libc::c_int, height: libc::c_int) -> libc::c_int;
    fn clear_buffer() -> libc::c_int;
    fn destroy() -> libc::c_int;
    fn update_buffer() -> libc::c_int;
    fn draw_line(x1: libc::c_int, y1: libc::c_int, x2: libc::c_int, y2: libc::c_int) -> libc::c_int;
    fn set_color(r: libc::c_int, g: libc::c_int, b: libc::c_int, a: libc::c_int) -> libc::c_int;
}

fn main() {
	
	let title = CString::new("hello?").unwrap();
	let rc : i32;
	
	unsafe {
		rc = init(title.as_ptr(), 480, 320);
	}
	
    println!("howdy: {}", rc);
	
	for _ in 0..10000 {
		
		unsafe {
			set_color(125, 125, 125, 255);
			draw_line(0, 0, 200, 200);
			update_buffer();
		}
		
	}
	
	unsafe {
		destroy();
	}
}
