#include <bits/stdc++.h>
using namespace std;
const int BUF_SZ = 1 << 22;
const int N = 1e5 + 30;
const int SQ = 1100;
const int SQ2 = N / SQ + 5;

//copy pasta from https://github.com/cpinitiative/usaco-guide/blob/0cdbdeb1ae60f586b3ecf3df98b6b99dbb80b3c6/content/1_General/Fast_IO.mdx
inline namespace Input {
	char buf[BUF_SZ];
	int pos;
	int len;
	char next_char() {
		if (pos == len) {
			pos = 0;
			len = (int)fread_unlocked(buf, 1, BUF_SZ, stdin);
			if (!len) return EOF;
		}
		return buf[pos++];
	}
	int read() {
		int x;
		char ch;
		while (!isdigit(ch = next_char()));
		x = ch ^ 48;
		while (isdigit(ch = next_char())) x = 10 * x + (ch ^ 48);
		return x;
	}
}
inline namespace Output {
	char buf[BUF_SZ];
	int pos;
	void flush_out() {
		fwrite_unlocked(buf, 1, pos, stdout);
		pos = 0;
	}
	void write_char(char c) {
		if (pos == BUF_SZ) flush_out();
		buf[pos++] = c;
	}
	void write(int x) {
		static char num_buf[100];
		int len = 0;
		for (; x >= 10; x /= 10) { num_buf[len++] = (char)(48 ^ (x % 10)); }
		write_char((char)(48 ^ x));
		while (len) write_char(num_buf[--len]);
		write_char('\n');
	}
	void init_output() { assert(atexit(flush_out) == 0); }
}

int n, m, a[2 * N], fin[N];

struct block {
	short cnt[N], bit[N];
	int L, R;
	vector<array<int, 2>> changes;
	
	void add(int r, short d) { cnt[r] += d; for (; r < N; r |= (r + 1)) bit[r] += d; }
	void apply() {
		if (changes.empty()) return;
		for (int i = changes.size() - 1; i >= 0; i--) {
			const auto &a = changes[i];
			fin[a[0]] = fin[a[1]];
		}
		for (int i = L; i < R; i++) a[i] = fin[a[i]];
		for (const auto &a: changes) fin[a[0]] = a[0], fin[a[1]] = a[1];
		changes.clear();
	}
	void Qchange(int x, int y) {
		if (!cnt[x] || x == y) return;
		changes.push_back({x, y});
		add(y, cnt[x]);
		add(x, -cnt[x]);
	}
} B[SQ2];


void change(int l, int r, int x, int y) {
	int cl = l / SQ, cr = r / SQ;
	B[cl].apply();
	B[cr].apply();
	if (cl == cr) {
		short C = 0;
		for (int i = l; i <= r; i++) if (a[i] == x) {
			C++;
			a[i] = y;
		}
		B[cl].add(x, -C);
		B[cl].add(y, C);
		return;
	}
	short C = 0;
	for (int i = l, end = (cl + 1) * SQ; i < end; i++) if (a[i] == x) {
		C++;
		a[i] = y;
	}
	B[cl].add(x, -C);
	B[cl].add(y, +C);

	C = 0;
	for (int i = cr * SQ; i <= r; i++) if (a[i] == x) {
		C++;
		a[i] = y;
	}
	B[cr].add(x, -C);
	B[cr].add(y, +C);

	for (int i = cl + 1; i < cr; i++)
		B[i].Qchange(x, y);	
}

int S(int l, int r, int pos, int p) {
	int cl = l / SQ, cr = r / SQ;
	B[cl].apply();
	B[cr].apply();
	if (cl == cr) {
		short s = 0;
		for (int i = l; i <= r; i++) s += pos <= a[i] && a[i] < pos + p;
		return s;
	}
	int s = 0;
	for (int i = l, end = (cl + 1) * SQ; i < end; i++) s += pos <= a[i] && a[i] < pos + p;
	for (int i = cr * SQ; i <= r; i++) s += pos <= a[i] && a[i] < pos + p;
	for (int i = cl + 1; i < cr; i++) s += B[i].bit[pos + p - 1];
	return s;
}

void get(int l, int r, int sum) {
	int pos = 0;
	for (int p = 1 << 16; p; p >>= 1) if (p + pos <= N) {
		int s = S(l, r, pos, p);
		if (s < sum) {
			pos += p;
			sum -= s;
		}
	}
	write(pos);
}

signed main() {
	iota(fin, fin + N, 0);
	init_output();
	n = read(), m = read();
	for (int i = 0; i < n; i++)
		a[i] = read();
	
	for (int i = 0; i < SQ2; i++) {
		B[i].L = i * SQ, B[i].R = (i + 1) * SQ;
		for (int j = B[i].L; j < B[i].R; j++)
			B[i].add(a[j], +1);
	}

	for (int i = 0; i < m; i++) {
		int t, l, r, x, y;
		assert(l < N && r < N && x < N && y < N);
		t = read(), l = read(), r = read(), x = read();
		t--, l--, r--;
		if (!t) {
			y = read();
			change(l, r, x, y);
		}
		else {
			get(l, r, x);
		}
	}
	return 0;
}
