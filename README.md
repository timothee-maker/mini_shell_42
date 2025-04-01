MINISHEll 42 | Par Thimothée NOLENT et Louis DE GUILLEBON

Parsing : 
- Sépare chaque pipe de la ligne en une liste chainee de plusieurs elements par pipe
- Associe un token et un argument a chaque élément en fonction de leur nature (CMD, ARG, INFILE ...)
- Renvoie cette liste

Exec :
- Crée une structure pour chaque ligne
- Crée une commande par pipe
- Redirige tous les arguments et infile dans un fichier créé appelé ".infile"
- Redirige ".infile" sur STDIN au moment de l'execve
- Redirige un fichier nommé ".outfile" sur STDOUT au moment de l'execve
- Exécute la commande
- Affiche le contenu de ".outfile" si pas de pipe derriere
- Clear ".infile"
- Ajoute le contenu de ".outfile" dans ".infile" si il y a un pipe apres
- Clear ".outfile"
