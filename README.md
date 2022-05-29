# 42sh

## Features

<details>
  <summary>Aliases</summary>
  <br>
  <p>Making up new commands as abbreviations for longer, more complex commands:</p>
  <ul>
    <li><code>alias</code> lists all aliases</li>
    <li><code>alias name</code> displays the value of this alias</li>
    <li><code>alias name [word_list]</code> sets <code>word_list</code> as the value for <code>name</code></li>
    <li><code>unalias [name1, name2...]</code> remove the given aliases. <code>*</code> is supported.</li>
  </ul>
  <p>Special aliases supported:</p>
  <ul>
    <li><code>precmd</code> runs just before each prompt is printed</li>
    <li><code>cwdcmd</code> runs after every change of working directory</li>
  </ul>
</details>

<details>
  <summary>History</summary>
  <br>
  <p>Invoking previous commands using command history:</p>
  <ul>
    <li><code>!!</code> executes the previous command</li>
    <li><code>!n</code> executes the nth command that was previously executed</li>
    <li><code>!-n</code> executes the command that was executed n commands ago</li>
    <li><code>!string</code> executes the most recently executed command that starts with string</li>
    <li><code>history</code> displays the previous commands with their index and time of execution (<code>hh:mm</code>)
  </ul>
  A <code>.42sh_history</code> file is also stored in the user's home folder to have a persistent history between sessions.
</details>

## Developers
| [<img src="https://github.com/EdenComp.png?size=85" width=85><br><sub>Florian Lauch</sub>](https://github.com/EdenComp) | [<img src="https://github.com/Steci.png?size=85" width=85><br><sub>Léa Guillemard</sub>](https://github.com/Steci) | [<img src="https://github.com/Croos3r.png?size=85" width=85><br><sub>Dorian Moy</sub>](https://github.com/Croos3r) | [<img src="https://github.com/RezaRahemtola.png?size=85" width=85><br><sub>Reza Rahemtola</sub>](https://github.com/RezaRahemtola)
| :---: | :---: | :---: | :---:
