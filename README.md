# electric_piano　電子ピアノ
子供からずっと音楽の夢が持っています。今は気持ちも変わらない、ですから、工学部を進学しても、音楽は趣味の一部分として続けつつ、情報学と電気系の専門知識を見つけて、活用して、このプロジェクトが出来ました。
どうぞ、ご清聴ください。
I use the stm32 and keil5 to develop a software piano and show little star or canon in C.

## まずは一度演奏を演示しましょう！
[http]

## 原理グラフ　電路
まずは電路図からご説明行きたいと思います。
![取扱い書とPCB](https://github.com/KokoroSinx/electric_piano/blob/main/PDF格式的原理图和PCB.jpg?raw=true)

![電路](https://github.com/KokoroSinx/electric_piano/blob/main/PDF格式的原理图和PCB2.jpg?raw=true)

- 如图所示，按键部分默认一端接地，另一端高电平。当不进行任何操作时，开关断开。按下按键后，高低电平两侧接通，程序检测到电势变化，随后执行命令程序。
- 図に示されているように、ボタン部分は通常、片側が接地に接続され、もう片側は高い電圧に接続されています。何も操作していないと、スイッチはオープンです。ボタンを押すと、高電圧と低電圧の2つの側が接続され、プログラムは電位の変化を検出し、その後コマンドプログラムを実行します。
## ソフトウェア　コード
つぎのコードは、組み込みCプログラムで、ハードウェアデバイスを制御するためのものです。具体的には、次のタスクを実行します。

1. ライブラリとヘッダーファイルのインクルード：コードの冒頭で、ハードウェアとのやり取りに必要な関数と定義を提供するいくつかのライブラリとヘッダーファイルが含まれています。
2. グローバル変数とマクロの定義：コード中でいくつかのグローバル変数、例えばボタンの状態やフラグビット、およびコード内でGPIOコントロール、LEDコントロール、および7セグメントディスプレイの表示を簡素化するためのいくつかのマクロが定義されています。
3. 音楽の再生：GPIOピンとタイマーの制御を使用して、音楽を再生する機能が実装されています。異なる音程の音符を再生でき、コードにはいくつかの音楽メロディの例が提供されています。
4. ボタン処理：ボタンの状態を検出および処理し、ボタンが押されたときに音楽の再生、停止、リプレイのトリガーなどのイベントが発生します。このコードにはボタンのデバウンス機能も含まれており、ボタンの安定な押下およびリリースを確保します。
5. 7セグメントディスプレイの表示：7セグメントディスプレイのピン状態を制御して、数字の表示機能が実現されています。コードにはディスプレイされる数字の配列が定義されています。

**ですので、１−７はdo re mi fa so ra si別々。しかし、８は演奏したメロディを再生することができる。コードについて詳しいの部分はこのGitHubに公開されています。**

## ハドウェア
主にSTM32F103C8T6
### 表
![omote](https://github.com/KokoroSinx/electric_piano/blob/main/实物照片.png?raw=true)

###裏
![ura](https://github.com/KokoroSinx/electric_piano/blob/main/实物照片%20(2).JPG?raw=true)

###完成！
![finish](https://github.com/KokoroSinx/electric_piano/blob/main/实物照片%20(1).JPG?raw=true)
