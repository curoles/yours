//https://wiki.scala-lang.org/display/SW/Parser+Combinators--Getting+Started
package yours

import scala.util.parsing.combinator._

class SentenceParser extends RegexParsers {

  val periodMark = "."
  val exclamationMark = "!"
  val questionMark = "?"
  val comma = ","
  def terminal: Parser[Any] = periodMark | exclamationMark | questionMark

  val hyphen = "-"

  val singleWord = """[a-zA-Z]+""".r
  val number = """[0-9]+""".r

  def compoundWord: Parser[Any] = singleWord ~ hyphen ~ singleWord

  def word: Parser[Any] = compoundWord | singleWord | number
 
  def words: Parser[Any] = rep(word ~ opt(comma))

  def sentence: Parser[Any] = words ~ terminal
}
