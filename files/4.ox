# Loop
for i = 0 | i < 5 | ++i
  print("Shoud be printed 5 times")
end

var continue? : Bool = true
var i : Int = 5
while continue?
  if i == 0
    continue? = false
  else
    i = i - 1
  end

  print(i)
end
