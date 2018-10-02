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

    let (sorted, cnt) = bubble_sort((&v).iter().collect());
    let st: String = sorted
        .iter()
        .map(|i| i.to_string())
        .collect::<Vec<String>>()
        .join(" ");
    println!("{}\n{}", st, cnt)
}

fn bubble_sort<T: Ord+Copy>(v: Vec<T>) -> (Vec<T>, usize) {
    match step(v) {
        (p, 0) => (p, 0),
        (p, cnt) => {
            let (p, pcnt) = bubble_sort(p);
            (p, cnt + pcnt)
        }
    }
}

fn step<T: Ord+Copy>(v: Vec<T>) -> (Vec<T>, usize) {
    match (v.get(0), v.get(1)) {
        (Some(&a), Some(&b)) => {
            let (&a, &b, cnt) = swap(&a, &b);
            let (p, pcnt) = step::<T>(insert_head(b, v[2..].into()));
            (insert_head(a, p), cnt + pcnt)
        }
        _ => (v, 0),
    }
}

fn swap<'a, T: Ord>(a: &'a T, b: &'a T) -> (&'a T, &'a T, usize) {
    match a.cmp(&b) {
        Ordering::Greater => (b, a, 1),
        _ => (a, b, 0),
    }
}

fn insert_head<T: Copy>(a: T, p: Vec<T>) -> Vec<T> {
    [vec![a], p]
        .into_iter()
        .flat_map(|s| s.into_iter().map(|&i| i))
        .collect()
}
