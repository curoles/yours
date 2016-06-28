/* Copyright Igor Lesik 2016
 *
 * Tools to parse text and tokenize words.
 */
package yours.grammar

import scala.util.parsing.combinator._


/** Parses sentence and creates list of tokens.
  *
  * author Igor Lesik
  *
  * Pretty much tokenizer on steroids, each Token is
  * not just a string, but case-class, so we know type/ID of a Token.
  *
  * [[file:SentenceParser.scala.html Source code]]
  *
  * @example Usage
  * {{{
  * val sentenceParser = new SentenceParser
  * val sentences = sentenceParser.parseAll(sentenceParser.text, text)
  * }}}
  *
  *
  *
  * About Scala Parser see:
  * [[https://wiki.scala-lang.org/display/SW/Parser+Combinators--Getting+Started]]
  *
  * @groupdesc Grammar Parsing rules.
  *
  */
class SentenceParser extends RegexParsers {

  /** End of sentence symbol definition
    * @group Grammar
    */
  def terminal: Parser[TerminalToken] =
    (PeriodMark | ExclamationMark | QuestionMark) ^^ {
      case str => TerminalToken(str)
    }

  /** Comma definition
    * @group Grammar
    */
  def comma: Parser[Token] =
    Comma ^^ {case a => CommaToken()}

  /** Simple single word regexp
    * @group Grammar
    */
  val SingleWord = """[a-zA-Z]+""".r

  /** Single word definition
    * @group Grammar
    */
  def singleWord: Parser[Token] =
    SingleWord ^^ {case str => SingleWordToken(str)}

  /** Whole number regexp
    * @group Grammar
    */
  val Number = """[0-9]+""".r

  /** Whole number definition
    * @group Grammar
    */
  def number: Parser[Token] =
    Number ^^ {case str => NumberToken(str)}

  /** Compound word with '-'
    * @group Grammar
    */
  def compoundWord: Parser[Token] =
    SingleWord ~ Hyphen ~ SingleWord ~
    opt(rep(Hyphen ~ SingleWord)) ^^ {
      case a ~ b ~ c => CompoundWordToken(a+b+c)
    }

  /** Any word or number definition
    * @group Grammar
    */
  def word: Parser[Token] =
    compoundWord | singleWord | number
 
  /** List of words separated by ','
    * @group Grammar
    */
  def words: Parser[List[Token]] =
    rep(word | comma)

  /** Sentence is list of words and end-of-sentence symbol
    * @group Grammar
    */
  def sentence: Parser[SentenceToken] =
    words ~ terminal ^^ {
      case ws ~ t => SentenceToken(ws, t)
    }

  /** Text is list of sentences
    * @group Grammar
    */
  def text: Parser[List[SentenceToken]] =
    rep(sentence)
}
