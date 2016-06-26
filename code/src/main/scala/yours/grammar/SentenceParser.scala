package yours.grammar

import scala.util.parsing.combinator._


/** Parses sentence and creates list of tokens.
 *
 *  Pretty much tokenizer on steroids, each Token is
 *  not just a string, but case-class, so we know type of a Token.
 *
 *  @author Igor Lesik
 *
 *  About Scala Parser see:
 *  [[https://wiki.scala-lang.org/display/SW/Parser+Combinators--Getting+Started]]
 *
 */
class SentenceParser extends RegexParsers {

  def terminal: Parser[Token] =
    (PeriodMark | ExclamationMark | QuestionMark) ^^ {
      case str => TerminalToken(str)
    }

  def comma: Parser[Token] =
    Comma ^^ {case a => CommaToken()}

  val singleWord = """[a-zA-Z]+""".r
  val number = """[0-9]+""".r

  def compoundWord: Parser[Any] =
    singleWord ~ Hyphen ~ singleWord ~
    opt(rep(Hyphen ~ singleWord)) /*^^ {
      case a ~ None => CompoundWordToken(str)
    }*/

  def word: Parser[Any] = compoundWord | singleWord | number
 
  def words: Parser[Any] = rep(word | comma)

  def sentence: Parser[Any] = words ~ terminal
}
