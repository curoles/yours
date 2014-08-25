=begin rdoc

Description::  Yours entry point
Copyright::    Igor Lesik 2012-2014
Author::       Igor Lesik
License::      Distributed under the Boost Software License, Version 1.0.
               (See  http://www.boost.org/LICENSE_1_0.txt)

=end

module Yours

class Main
  def initialize
    #@io = Yours::Interact::IO.new
  end

  def run
    puts 'Yours Operating User Reactive System'
    #YoursOptions.parse(ARGV)
    #@io.interact
  end

end

end # module Yours

yours = Yours::Main.new
yours.run

