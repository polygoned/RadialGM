#include "ArtManager.h"

#include <QDirIterator>
#include <QPixmapCache>

QHash<QString, QIcon> ArtManager::icons;
QBrush ArtManager::transparenyBrush;

void ArtManager::Init() {
  QDirIterator it(":/resources", QDirIterator::Subdirectories);
  while (it.hasNext()) {
    QString path = it.next();
    QString name = path.mid(path.lastIndexOf("/") + 1, path.lastIndexOf(".") - 1 - path.lastIndexOf("/"));
    icons[name] = QIcon(path);
  }

  transparenyBrush = QBrush(Qt::black, QPixmap(":/transparent.png"));

  QPixmapCache::setCacheLimit(500000);  // 500mb cache limit
}

ArtManager::ArtManager() {}

const QIcon& ArtManager::GetIcon(const QString& name) {
  if (!icons.contains(name)) icons[name] = QIcon(name);

  return icons[name];
}

const QBrush& ArtManager::GetTransparenyBrush() { return transparenyBrush; }

bool ArtManager::GetCachedPixmap(const QString& name, QPixmap &pm) {
//  QPixmap pm;
  if (!QPixmapCache::find(name, &pm)) {
    if (!pm.load(name)) return false;
     QPixmapCache::insert(name, pm);
  }
  return true;
  //  return std::move(pm);
}

void ArtManager::clearCache() { QPixmapCache::clear(); }
