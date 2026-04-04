original  
<https://www.inworks.jp/download/oyainput>  
<https://github.com/inwskatsube/oyainput>  


# このソフトについて

当ソフトは Linux で羊配列入力を可能にするため、アイ・エヌ・ワークス様開発の oyainput を独自にカスタマイズしたものです。
インプットメソッドフレームワークは fcitx を想定しており、fcitx5 には対応していません。


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
当ソフトの同時打鍵アルゴリズムは日笠健氏開発の『親指ひゅんＱ』の付属資料である「同時打鍵ステートマシン」の項にあるアルゴリズムに基づき実装しました。貴重な資料を公開いただいた日笠氏に深く感謝いたします。