use std::io::*;
use std::str::FromStr;

fn read<T: FromStr>() -> Option<T> {
    let stdin = stdin();
    let stdin = stdin.lock();
    let token: String = stdin
        .bytes()
        .flat_map(|c| c)
        .map(|c| c as char)
        .skip_while(|c| c.is_whitespace())
        .take_while(|c| !c.is_whitespace())
        .collect();
    token.parse().ok()
}

enum Token {
    Op(char),
    Num(isize),
}

impl FromStr for Token {
    type Err = Error;
    fn from_str(s: &str) -> Result<Self> {
        let num: Option<isize> = (*s).parse().ok();
        let ch: Option<char> = (*s).parse().ok();
        match (num, ch) {
            (Some(n), _) => Ok(Token::Num(n)),
            (_, Some(c)) => Ok(Token::Op(c)),
        }
    }
}

fn main() {
    let v: Box<Iterator<Item=Token>> = Box::new(std::iter::repeat(0).map(|_| read()).flat_map(|e| e));

    let (sorted, cnt) = calc(v);
    let st: String = sorted
        .iter()
        .map(|i| i.to_string())
        .collect::<Vec<String>>()
        .join(" ");
    println!("{}\n{}", st, cnt)
}

fn calc(v: Box<Iterator<Item=Token>>) -> (char, isize, isize) {
    let h = match v.take(1).next() {
        Some(Token::Op(c)) => c(c),

    };
    let a = v.skip(1);
    (h, Box::new(a))
}

fn c(op: char, lhr: isize, rhl: isize) -> isize {
    0
}
