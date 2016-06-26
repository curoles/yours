
# To be sourced

custom_ruby()
{
  local RUBY=$1
  echo Custom Ruby: $RUBY
  export PATH=$RUBY:$PATH:
}

custom_cmake()
{
  local CMAKE=$1
  echo Custom cmake: $CMAKE
  export PATH=$CMAKE:$PATH:
}

custom_ruby /tools/local/ruby-2.1.0/bin/
custom_cmake /sw/tools/bin/cmake-2.8.3/bin/


