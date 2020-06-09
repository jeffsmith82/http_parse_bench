use std::time::{Duration, Instant};
fn main() {
    let response = String::from("HTTP/1.1 418 I'm a teapot\r\n");
    let mut res: (&str, &str, &str) = ("", "", "");
    let start = Instant::now();
    for _ in 0..100_000_000 {
        res = match parse_http(&response) {
            Ok(data) => data,
            Err(e) => {
                println!("{}", e);
                continue;
            }
        };
    }
    let duration = start.elapsed();

    println!("version:{}\ncode:{}\ndescription:{}\n", res.0, res.1, res.2);
    println!("Time elapsed in parse_response() is: {:?}", duration);
}

fn parse_http(s: &str) -> Result<(&str, &str, &str), &str> {
    let mut parts = s.splitn(3, ' ');
    let version = parts.next().ok_or("No Version")?;
    let code = parts.next().ok_or("No status code")?;
    let description = parts.next().ok_or("No description")?;
    Ok((version, code, description))
}
