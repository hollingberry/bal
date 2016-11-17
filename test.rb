def string_of(len)
  Σ = "()[]".chars
  (0..len).map { Σ[rand(4)] }.join
end

def valid?(str)
  system "./bal '#{str}' >/dev/null 2>&1"
  return $? == 0 ? true : false
end

begin
  (0..16).each do |len|
    (4 ** len).times do
      s = string_of(len)
      puts(s) if valid?(s)
    end
  end
rescue Interrupt
  puts
end
