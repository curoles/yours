=begin rdoc

Description::  Simple Telnet Server
Copyright::    Igor Lesik 2014
Author::       Igor Lesik
License::      Distributed under the Boost Software License, Version 1.0.
               (See  http://www.boost.org/LICENSE_1_0.txt)

http://ptspts.blogspot.com/2011/04/how-to-write-simple-echo-and-chat.html
=end

require 'socket'  # TCPServer

module Yours

class TelnetServer

  def initialize(port = 1233)
    @tcp_server = TCPServer.new("127.0.0.1", port)
  end

  def run
    loop do
      accepted_sock = accept_connection(@tcp_server)
      break unless accepted_sock

      Thread.start(accepted_sock) do |s|
        begin
        while line = s.gets;  # Returns nil on EOF.
          (s << "You wrote: #{line.inspect}\r\n").flush
        end
        rescue
          bt = $!.backtrace * "\n  "
          ($stderr << "error: #{$!.inspect}\n  #{bt}\n").flush
        ensure
          s.close
        end
      end
    end
  end

  def stop
    puts "Stopping telnet server..."
    @tcp_server.close #interrupt socket blocking calls
  end

  private

  #
  # Returns socket object or nil if IO.select was interrupted
  #
  def accept_connection(serv)
    begin # emulate blocking accept
      sock = serv.accept_nonblock
    rescue IO::WaitReadable, Errno::EINTR
      begin
        IO.select([serv])
      rescue
        puts 'TelnetServer IO.select interrupted'
        return nil
      end
      retry #select returned Ok so try to accept again
    end
    # sock is an accepted socket now
    sock
  end
end

end # module Yours
