Dim s
' Выводим строку на экран
do
WScript.StdOut.WriteLine "Menu:"
WScript.StdOut.WriteLine "----------------------------"
WScript.StdOut.WriteLine "1. Information about the author"
WScript.StdOut.WriteLine "2. Delete contents of specified folder"
WScript.StdOut.WriteLine "3. Creating a shortcut to a given network resource"
WScript.StdOut.WriteLine "4. Exit"
WScript.StdOut.WriteLine "----------------------------"
WScript.StdOut.WriteLine "Select a menu item:"
' Считываем строку
s = WScript.StdIn.ReadLine
' Создаем объект WshShell
Set WshShell = WScript.CreateObject("WScript.Shell")
if (s="1") Then
    WScript.StdOut.WriteLine "Yury Evzhenko, ITI-12"
elseif(s="2") Then
    WScript.StdOut.Write "Enter the name of the folder:"
    Dim a
    a=WScript.StdIn.ReadLine
    WshShell.run "test.cmd """ & a & """ "
elseif(s="3") Then
Set FSO = WScript.CreateObject("Scripting.FileSystemObject")
    WScript.StdOut.Write "Enter the name of the shortcut:"
    f = WScript.StdIn.ReadLine
    ' Создаем ярлык на сетевой ресурс
    Set oUrlLink = WshShell.CreateShortcut(f+".URL")
    WScript.StdOut.Write "Enter the resource name:"
    r = WScript.StdIn.ReadLine
    ' Устанавливаем URL
    oUrlLink.TargetPath = r
    ' Сохраняем ярлык
    oUrlLink.Save
Set WshFldrs = WshShell.SpecialFolders
PathCopy = WshFldrs.item("Desktop")+"\"
Set F = FSO.GetFile(f+".URL")
F.Copy PathCopy
End if
    loop until (s="4")