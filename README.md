YOURS - Yours Operating User Reactive System
============================================

How to use GitHub
=================

First you have to make sure that git is installed on your system, for example:
```
which git
```

If you have not used git on your system before, then you have to setup/configure it first:
http://git-scm.com/book/en/Getting-Started-First-Time-Git-Setup

Create source directory
```
cd ~/prj/github
mkdir -p yours/yours
cd yours/yours
```

Initialize git
```
git init
```

If you need to use different user name for this project
```
yours>git config user.name "username"
yours>git config user.email username@yahoo.com
```

Create a remote named "origin" pointing at your GitHub repository
```
git remote add origin https://github.com/curoles/yours.git
```

Pull sources
```
git pull origin master
```

Commit changes

```
git add ...
git commit -a -m "comments" <files>
git push
```

