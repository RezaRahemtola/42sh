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
    <li><code>!-n</code> executes the command that was executed <code>n</code> commands ago</li>
    <li><code>!string</code> executes the most recently executed command that starts with <code>string</code></li>
    <li><code>!?string</code> executes the most recently executed command that contains <code>string</code></li>
    <li><code>history [nb]</code> displays the previous commands (up to <code>nb</code> if specified) with their index and time of execution (<code>hh:mm</code>)</li>
  </ul>
  A <code>.42sh_history</code> file is also stored in the user's home folder to have a persistent history between sessions.
</details>

<details>
  <summary>Line editing</summary>
  <br>
  <ul>
    <li><code>↑</code> and <code>↓</code> to select a command from the history to edit/execute</li>
    <li><code>←</code> and <code>→</code> to move in the input and edit it</li>
    <li><code>CTRL</code> + <code>L</code> to clear the screen</li>
  </ul>
</details>

<details>
  <summary>Local environment</summary>
  <br>
  <p>Variables specific to the current shell:</p>
  <ul>
    <li><code>set var = val</code> creates/updates <code>var</code> with <code>val</code></li>
    <li><code>set var1 var2 ...</code> creates/updates several variables with empty values</li>
    <li><code>-r</code> is an option that can be used with <code>set</code> for a read-only variable, which means that you won't be able to use <code>set</code> or <code>unset</code> on it again.</li>
    <li><code>unset var1 var2 ...</code> removes the given variables</li>
  </ul>
  <p>Preloaded variables:</p>
  <ul>
    <li><code>cwd</code> for the current working directory (will be updated when you change directory)</li>
    <li><code>euid</code> for the effective user id</li>
    <li><code>euser</code> for the effective username</li>
    <li><code>gid</code> for the user's group id</li>
    <li><code>group</code> for the user's group name</li>
    <li><code>history</code> explained below, set to <code>100</code> by default</li>
    <li><code>home</code> for the user's home directory</li>
    <li><code>owd</code> for the old working directory (will be updated when you change directory)</li>
    <li><code>uid</code> for the user id</li>
    <li><code>user</code> for the username</li>
  </ul>
  <p>Special variables supported:</p>
  <ul>
    <li><code>ignoreeof</code> to disable EOF shell exit if set to <code>0</code> or empty. If set to a number <code>n</code>, the shell will exit on the nth consecutive EOF.</li>
    <li><code>history</code> to set a limit of commands display by the builtin of the same name.</li>
  </ul>
</details>


## Developers
| [<img src="https://github.com/EdenComp.png?size=85" width=85><br><sub>Florian Lauch</sub>](https://github.com/EdenComp) | [<img src="https://github.com/Steci.png?size=85" width=85><br><sub>Léa Guillemard</sub>](https://github.com/Steci) | [<img src="https://github.com/Croos3r.png?size=85" width=85><br><sub>Dorian Moy</sub>](https://github.com/Croos3r) | [<img src="https://github.com/RezaRahemtola.png?size=85" width=85><br><sub>Reza Rahemtola</sub>](https://github.com/RezaRahemtola)
| :---: | :---: | :---: | :---:
