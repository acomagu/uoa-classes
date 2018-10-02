use std::cmp::Ordering;
use std::io::*;
use std::str::FromStr;

fn read<T: FromStr>() -> T {
    let stdin = stdin();
    let stdin = stdin.lock();
    let token: String = stdin
        .bytes()
        .map(|c| c.expect("failed to read char") as char)
        .skip_while(|c| c.is_whitespace())
        .take_while(|c| !c.is_whitespace())
        .collect();
    token.parse().ok().expect("failed to parse token")
}

fn main() {
    let n: usize = read();
    let v: Vec<isize> = (0..n).map(|_| read()).collect();

    let (sorted, cnt) = selection_sort::<&isize>((&v).iter().collect());
    let st: String = sorted
        .iter()
        .map(|i| i.to_string())
        .collect::<Vec<String>>()
        .join(" ");
    println!("{}\n{}", st, cnt)
}

fn selection_sort<T: Ord + Copy>(v: Vec<T>) -> (Vec<T>, usize) {
    match v.get(0) {
        Some(&e) => {
            let (a, p, c) = step(v, e);
            let (pp, cc) = selection_sort(p.collect::<Vec<_>>()[1..].into());
            (insert_head(pp.into_iter(), a).collect(), c + cc)
        }
        None => (vec![], 0),
    }
}

fn step<'a, T: Ord + Copy + 'a>(v: Vec<T>, s: T) -> (T, Box<Iterator<Item = T> + 'a>, usize) {
    match v.get(0) {
        Some(&e) => {
            let (a, p, _) = step(v[1..].into(), s);
            match e.cmp(&a) {
                Ordering::Greater => (a, Box::new(insert_head(p, e)), 1),
                _ => (e, Box::new(insert_head(v[1..].to_vec().into_iter(), s)), 0),
            }
        }
        None => (s, Box::new(v.into_iter()), 0),
    }
}

fn insert_head<T, I: Iterator<Item = T>>(v: I, e: T) -> std::iter::Chain<std::vec::IntoIter<T>, I> {
    vec![e].into_iter().chain(v)
}
