original  
<https://www.inworks.jp/download/oyainput>  
<https://github.com/inwskatsube/oyainput>  


# このソフトについて

Linuxで親指シフト入力を可能にするためのソフトウェアです。  
MozcやAnthy、libkccなど、主要な日本語入力システムに対応します。  
インプットメソッドフレームワークはfcitxを想定していますが、ibusやuimでも利用可能です。  
新しめのLinuxならだいたい動くはずですが、開発時はUbuntu16.04LTSで動作確認しています。
  
# インストール方法
  
ターミナルから以下のコマンドを入力します。

    $ git clone https://github.com/hitsuj256/oyainputh.git
    $ cd oyainputh
    $ make clean; make; sudo make install

インストールには管理者(root)権限が必要です。  
またGCC、makeが必要ですので、もしエラーになる場合は apt-get などで事前に導入しておいてください。

    $ sudo apt-get install -y make gcc


# 起動方法

    $ oyainput [username]

usernameは利用するユーザー名を指定します。  
省略した場合は、現在のログインユーザー名になります。  
もしsuコマンドなどで管理者(root)モードでターミナルにログインしている場合はrootユーザのホームディレクトリを見に行くことになりますので、[username]は省略しないことをおすすめします。


# 設定ファイルについて
設定ファイルは、初回起動時にホームディレクトリ下に以下の名前で作成されます。

    (HOMEDIR)/.oyainputconf

# Mozcの設定
「Mozcの設定」の「一般」タブの「ローマ字テーブル」にて定義の追加が必要な場合があります。

| 入力 | 出力 |
|----|----|
| /  | ／ |
| z/ | ・ |
| z- | 〜 |
| z. | … |


# 謝辞
当ソフトは、アイ・エヌ・ワークス様開発の oyainput を当方の思いつきで勝手に改造したものです。
素晴らしいソフトウェアを公開いただいたことに深く感謝いたします。

