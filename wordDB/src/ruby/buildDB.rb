#!/usr/bin/env ruby
puts "Ruby version: #{RUBY_VERSION}"

require 'fileutils'

source_dir = ARGV[0]
dest_dir = ARGV[1]

puts "Arguments: #{source_dir} #{dest_dir}"

unless Dir.exist?(source_dir)
  puts "Source directory #{source_dir} does not exist"
  exit(1)
end

unless Dir.exist?(dest_dir)
  puts "Destination directory #{dest_dir} does not exist"
  exit(1)
end

abstracts = File.join(source_dir, 'abstract')

unless Dir.exist?(abstracts)
  puts "Directory 'abstract' #{abstracts} does not exist"
  exit(1)
end

dest_db = File.join(dest_dir, 'db')
FileUtils.rm_rf(dest_db)
Dir.mkdir(dest_db)

dest_db_abstract = File.join(dest_db, 'abstract')
Dir.mkdir(dest_db_abstract)

def word_to_trie_path(word)
  path = ''
  word.each_char do |char|
    path = File.join(path, char)
  end
  path
end

yaml_files_in_src = File.join(abstracts, "**", "*.yaml")
Dir.glob(yaml_files_in_src).each do |file_path|
  word = File.basename(file_path, '.yaml')
  if word.empty? then continue end
  trie_path = word_to_trie_path(word)
  word_dest_dir = word.length == 1 ? dest_db_abstract : File.join(dest_db_abstract, trie_path.chop)
  FileUtils.mkdir_p(word_dest_dir)
  dest_file_path = File.join(dest_db_abstract, trie_path+".yaml")
  puts "copy: #{file_path}, #{dest_file_path}"
  FileUtils.copy_file(file_path, dest_file_path)
end

