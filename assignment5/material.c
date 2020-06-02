#include "material.h"

PhongMaterial::PhongMaterial(const Vec3f &diffuse, 
    const Vec3f &specular, float e,
    const Vec3f &reflective, const Vec3f &transparent, 
    float ior) : Material(diffuse)
{
    specularColor = specular;
    exponent = e;
    reflectiveColor = reflective;
    transparentColor = transparent;
    indexOfRefraction = ior;
}

Vec3f PhongMaterial::getSpecularColor() const {
    return specularColor;
}

Vec3f PhongMaterial::getReflectiveColor() const {
    return  reflectiveColor;
}

Vec3f PhongMaterial::getTransparentColor() const {
    return transparentColor;
}

float PhongMaterial::getIndexOfRefraction() const {
    return indexOfRefraction;
}

Vec3f PhongMaterial::Shade(const Ray &ray, const Hit &hit, 
    const Vec3f &dirToLight, const Vec3f &lightColor) const
{
    Vec3f specular = specularColor;
    Vec3f diffuse = getDiffuseColor();

    Vec3f N = hit.getNormal();
    Vec3f V = ray.getDirection();
    Vec3f D = dirToLight;
    N.Normalize();
    V.Normalize();
    D.Normalize();
    Vec3f H = D - V;
    H.Normalize();

    float t = D.Dot3(N);
    if(t < 0) {
        return Vec3f(0,0,0);
    }
    diffuse *= t;

    float dot = pow(max(N.Dot3(H), (float)0), exponent);

    specular *= dot;

    return (specular + diffuse) * lightColor;
}

void PhongMaterial::glSetMaterial(void) const {

  GLfloat one[4] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat zero[4] = { 0.0, 0.0, 0.0, 0.0 };
  GLfloat specular[4] = {
    getSpecularColor().r(),
    getSpecularColor().g(),
    getSpecularColor().b(),
    1.0};
  GLfloat diffuse[4] = {
    getDiffuseColor().r(),
    getDiffuseColor().g(),
    getDiffuseColor().b(),
    1.0};
  
  // NOTE: GL uses the Blinn Torrance version of Phong...      
  float glexponent = exponent;
  if (glexponent < 0) glexponent = 0;
  if (glexponent > 128) glexponent = 128;
  
#if !SPECULAR_FIX 
    
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);
  
#else

  // OPTIONAL: 3 pass rendering to fix the specular highlight 
  // artifact for small specular exponents (wide specular lobe)

  if (SPECULAR_FIX_WHICH_PASS == 0) {
    // First pass, draw only the specular highlights
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &glexponent);
    
  } else if (SPECULAR_FIX_WHICH_PASS == 1) {
    // Second pass, compute normal dot light 
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, one);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zero);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  } else {
    // Third pass, add ambient & diffuse terms
    assert (SPECULAR_FIX_WHICH_PASS == 2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zero);
  }

#endif
}