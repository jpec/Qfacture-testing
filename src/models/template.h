#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <string>

using namespace std;


/**
 * Représente un template de facture
 */ 
class Template
{
public:
    
    /**
     * Énumération des types possibles de templates
     */
    enum Type {
        UNKNOWN,
        HTML,
        LATEX
    };
    
    Template();
    
    /**
     * Retourne l'identiant de ce template.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    int getId() const;
    
    /**
     * Définit le nom de ce template.
     *
     * @param name Le nouveau nom.
     */
    void setName(const string &name);

    /**
     * Retourne le nom de ce template.
     *
     * @return string Le nom
     */
    string getName() const;
    
    /**
     * Définit le type de ce template
     *
     * @param type Le type choisi
     */
    void setType(Type type);
    
    /**
     * Retourne le type de ce template.
     *
     * @return Le type du template.
     */
    Type getType() const;
    
    /**
     * Définit le contenu de ce template
     *
     * @param type Le contenu. Aucune vérification n'est effectuée quant à 
     *             sa validité, mis à pas un test de "non vacuité".
     */
    void setContent(const string &content);
    
    /**
     * Retourne le contenu de ce template.
     *
     * @return Le contenu du template.
     */
    string getContent() const;
    
private:
    /**
     * Identifiant du template
     */
	int id;
    
    /**
     * Nom du template (de manière à ce que l'utilisateur puisse les distinguer)
     */
	string name;
    
    /**
     * Type de template : html, latex, etc.
     */
	Type type;
    
    /**
     * Contenu du template
     */
	string content;
};

#endif // TEMPLATE_H
