#!/usr/bin/ruby

for i in 1..8 do
  dir = File.dirname(__FILE__)
  bin = dir + "/bin/duplicates"
  tests = dir + "/test/inputs/case-0#{i}"
  cat = bin + " " + tests
  result = `#{cat}`
  ccount = 0
  expected = File.read(dir + "/test/expected-outputs/case-0#{i}")
  if result.eql? expected then
    print "test #{i} passed\n"
  else
    print "\n\n*** Test #{i} Failed ***\n\n"
    print "-- expected output --\n" + expected + "\n"
    print "-- actual output --\n" + result + "\n"
    print "*** Test #{i} Failed ***\n\n\n"
  end
end
