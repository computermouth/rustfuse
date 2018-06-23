extern crate libc;

use std::ffi::CString;
use std::f64;
use std::thread;

extern {
    fn init(title: *const libc::c_char, width: libc::c_int, height: libc::c_int) -> libc::c_int;
    fn clear_buffer() -> libc::c_int;
    fn destroy() -> libc::c_int;
    fn update_buffer() -> libc::c_int;
    fn draw_point(x: libc::c_int, y: libc::c_int) -> libc::c_int;
    fn draw_line(x1: libc::c_int, y1: libc::c_int, x2: libc::c_int, y2: libc::c_int) -> libc::c_int;
    fn set_color(r: libc::c_int, g: libc::c_int, b: libc::c_int, a: libc::c_int) -> libc::c_int;
}

fn main() {
	
	let title = CString::new("hello?").unwrap();
	let rc : i32;
	
	unsafe {
		rc = init(title.as_ptr(), 1280, 720);
	}
	
    println!("howdy: {}", rc);
	
	let c1_x_origin = 639;
	let c1_y_origin = 100;
	let c1_radius = 30;
	
	let c2_x_origin = 639;
	let c2_y_origin = 500;
	let c2_radius = 100;
	
	for i in 0..600 {
		
		for j in 0..10 {
		
			unsafe {
				set_color(255, 255 , 255, ( j * 15 ) + 100 );
				
				let c1_angle = (  i + ( j * 5 )        % 360 ) as f64 * f64::consts::PI / 180.0;
				let c2_angle = ( (i + ( j * 5 ) + 180) % 360 ) as f64 * f64::consts::PI / 180.0;
				
				let x1 = c1_x_origin as f64 + c1_radius as f64 * c1_angle.cos();
				let y1 = c1_y_origin as f64 + c1_radius as f64 * c1_angle.sin();
				
				let x2 = c2_x_origin as f64 + c2_radius as f64 * c2_angle.cos();
				let y2 = c2_y_origin as f64 + c2_radius as f64 * c2_angle.sin();
				
				let x1 = x1 as i32;
				let y1 = y1 as i32;
				let x2 = x2 as i32;
				let y2 = y2 as i32;
				
				draw_line(x1, y1, x2, y2);
			}
		
		}
		
		unsafe {
			update_buffer();
		}
		
	}
	
	unsafe {
		destroy();
	}
}
