/* Copyright Igor Lesik 2016
 *
 * This file contains File System based Word DB class.
 */
package yours.word

import java.nio.file.{Paths, Files}

/** File System based Word DB.
  *
  * [[file:FileWordDB.scala.html]] in [[file:package.scala.html]]
  * 
  * @constructor does not do anything, call `open` 
  * @param path base dir path where all files located 
  */
class FileWordDB(path:String) extends WordDB(path) {

  /** Open and initialize */
  override def open(): Boolean = {
    println("WordDB working directory is " + path)
    val workingDir = Files.createDirectories(Paths.get(path))
    true
  }

  /** Returns True if word exists in DB.*/
  override def exists(word:String): Boolean = {
    find(word) match {
      case Some(_) => true
      case None => false
    }
  }

  /** Returns word if finds it, else `None` */ 
  override def find(word:String): Option[String] = {
    //TODO search cache
    val foundXmlFile = findFile(word, word+".xml")
    val xmlFile = foundXmlFile.get
    val wordDef = new WordDef
    wordDef.readXML(xmlFile)
    None
  }

  /** Returs word xml file path or `None` */
  def findFile(wordPath:String, fileName:String): Option[String] = {
    val hpath = this.path + toHPath(wordPath) + fileName
    if (!fileExists(hpath)) loadRemoteFile(fileName, hpath)
    if (fileExists(hpath)) Some(hpath) else None
  }

  /** Constructs H-path */
  def toHPath(s:String): String = {
    def appendPathDelim(x:Char) = x.toString + "/"
    s.flatMap(c => appendPathDelim(c))
  }

  /** Returns true if file exists */
  def fileExists(s:String) = Files.exists(Paths.get(s))

  /** Checks remote location(s) and copies file to local file system */
  def loadRemoteFile(fileName:String, destPathStr:String) = {
    val remoteLocation = "../yours/code/wordDB/"
    val remoteFilePath = Paths.get(remoteLocation+fileName)
    val destPath = Paths.get(destPathStr)
    Files.createDirectories(destPath.getParent())
    Files.copy(remoteFilePath, destPath)
  }
}

