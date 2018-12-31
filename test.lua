width=150.6
height = 200.7
vec={1,3,5,7,9}

function fib(n) 
  return n < 2 and n or fib(n - 1) + fib(n - 2) 
end
function fibs(n)
  vals = {}
  for i=1, n do
    vals[i] = fib(i)
  end
  return vals
end
