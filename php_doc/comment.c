/*
+----------------------------------------------------------------------+
| PHP Version 7                                                        |
+----------------------------------------------------------------------+
| Copyright (c) 1997-2018 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: No Name                                                      |
+----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <php_ini.h>
#include <zend_interfaces.h>
#include <ext/standard/info.h>


#include "tag.h"
#include "comment.h"

#include "scanner.h"
#include "parser.h"

#include <glib.h>


/* {{{ php_doc_comment_create */
php_doc_block*
php_doc_comment_create(char *comment) {
    php_doc_block *doc_block = g_new(php_doc_block, 1);
    char status = parseDocBlock(&comment, doc_block);

    if (status!=SUCCESS) {
        // TODO free tags
        g_free(doc_block);
        doc_block = NULL;
    }

    return doc_block;
}

php_doc_tag*
php_doc_comment_get_tag_by_name(php_doc_block *doc_block, char *tag_name) {
    php_doc_tag *tag = NULL;
    int i = 0;
    if (doc_block && doc_block->tags)
    while (NULL!=doc_block->tags[i]) {
        tag = doc_block->tags[i];
        if (0==g_strcmp0(tag->name, tag_name)) {
            break;
        }
        tag = NULL;
        i++;
    }

    return tag;
}

void
php_doc_comment_free(php_doc_block *comment) {
    int i;

    if (NULL!=comment) {

        for (i = 0; NULL!=comment->tags[i]; i++) {
            if (NULL!=comment->tags[i]->description) {
                g_free(comment->tags[i]->description);
            }
            if (NULL!=comment->tags[i]->name) {
                g_free(comment->tags[i]->name);
            }
            if (NULL!=comment->tags[i]->value) {
                g_free(comment->tags[i]->value);
            }
            g_free(comment->tags[i]);
        }
        if (NULL!=comment->tags) {
            g_free(comment->tags);
        }
        if (NULL!=comment->description) {
            g_free(comment->description);
        }

        g_free(comment);
    }

}


/* }}} */


#if 0


class A {
    /**
     * Description courte
     *
     * Ceci est `du code en ligne` %null, %false, #StdClass, $name
     *
     * Ceci est une description longue
     *
     *     Ceci est aussi un bloc de code sur plusieurs lignes.
     *     Il faut une ligne vide et une indentation d'au moins 4 espaces.
     *
     * ```c
     * GtkWidget *label = gtk_label_new ("Gorgeous!");
     * ```
     *      ```PHP
     *      $label = gtk_label_new("Gorgeous!");
     *      ```
     *      ```PHP8>
     *      $label = new Gtk\Label(label: "Gorgeous!");
     *      ```
     *      ```PHP7>
     *      $label = new Gtk\Label(['label'=> "Gorgeous!"]);
     *      ```
     *      ```PHP5>
     *      $label = new Gtk\Label("Gorgeous!");
     *      ```
     *      ```GTKML
     *      &lt;gtk:label text="Gorgeous!" lang="fr"/&gt;
     *      ```
     * @api
     * @see chemin()
     * @link http://www.spip.net/...
     * @param int|string|null $var description/comment
     * @return bool|string
     *     - int Nombre de lignes,
     *     - false en cas d'erreur.
     */
    function test() {

    }
}


$reflector = new ReflectionClass('Magicien');
$methods = $reflector->getMethods();
foreach($methods as $method) {
    $string = $method->getDocComment();
    $doc_reflector = new ReflectionDoc($string);
    $tag = $doc_reflector->getTag('return');
    $tags = $doc_reflector->getTags();
    foreach($tags as $tag) {
        $tag->getName();// @param
        $tag->getComment();// string
    }
    $description = $doc_reflector->getDescription();// Comment
    $blocks = $description->getBlocks();
    foreach($blocks as $block) {
        $block->isCode();
        $block->isText();
        $block->isConstant();
        $block->isVariable();
        $block->isFunction();
        $block->isMethod();
        $block->isClass();
    }
}

#endif
