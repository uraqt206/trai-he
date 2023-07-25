for((i=1; i<=50; ++i)); do
  echo $i
  ./gen > int
  ./rose < int > in1
  ./trau < int > in2
  diff -w in1 in2 || break
  # diff -w <(./rose < int) <(./trau < int) || break
done