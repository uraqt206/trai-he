  int q;
  cin >> q;

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << sum(r) - sum(l-1) << "\n";
  }
