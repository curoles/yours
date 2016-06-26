=begin rdoc

Description::  Yours entry point
Copyright::    Igor Lesik 2012-2014
Author::       Igor Lesik
License::      Distributed under the Boost Software License, Version 1.0.
               (See  http://www.boost.org/LICENSE_1_0.txt)

=end

require_relative 'version'
require_relative 'TelnetServer'

module Yours

class Main
  def initialize
    #@io = Yours::Interact::IO.new
    @telnet_server = Yours::TelnetServer.new
  end

  def run
    puts "Yours Operating User Reactive System #{Yours::VERSION}"
    #YoursOptions.parse(ARGV)
    #@io.interact
    @telnet_server.run
    puts "Exiting Yours, bye!"
  end

  def trap_signal_INT(signo)
    #exit(0)
    @telnet_server.stop
    Signal.trap(signo, "DEFAULT")
  end
end

end # module Yours


yours = Yours::Main.new

Signal.trap("INT") do |signo|
  puts "Signal: #{Signal.signame(signo)} (Ctrl-C)"
  yours.trap_signal_INT(signo)
end

yours.run

